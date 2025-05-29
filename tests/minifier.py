import argparse
import re
import fileinput
OPS = [
    '+', '-', '*', '/', '%', '++', '--',
    '+=', '-=', '*=', '/=', '%=', '=', '==', '!=',
    '&&', '||', '!', '&', '|', '^', '<<', '>>',
    '<', '>', '<=', '>=', '<<=', '>>=', '&=', '|=', '^=', ',',
    '(', ')', '{', '}', ';', 'else', ':', '::', '?'
]
SPACED_OPS = ['else']
UNARY_OPS= ["+", "-", "&", "!", "*"]
PREPROCESSOR_TOKEN = '#'
def remove_everything_between(subs1, subs2, line):
    regex = re.compile(subs1 + r'.*' + subs2)
    return regex.sub('', line)
def remove_everything_before(subs, line):
    regex = re.compile(r'.*' + subs)
    return regex.sub('', line)
def remove_everything_past(subs, line):
    regex = re.compile(subs + r'.*')
    return regex.sub('', line)
def remove_multiline_comments(lines):
    start, end = '/*', '*/'
    escaped_start, escaped_end = '/\\*', '\\*/'
    in_comment = False
    newlines = []
    for line in lines:
        if not in_comment:
            start_pos = line.find(start)
            if start_pos != -1:
                in_comment = True
                end_pos = line.find(end)
                if start_pos < end_pos:
                    line = remove_everything_between(escaped_start, escaped_end, line)
                    in_comment = False
                else:
                    line = remove_everything_past(escaped_start, line)
        else:
            end_pos = line.find(end)
            if end_pos != -1:
                line = remove_everything_before(escaped_end, line)
                in_comment = False
                start_pos = line.find(start)
                if start_pos != -1:
                    line = remove_everything_past(escaped_start, line)
                    in_comment = True
            else:
                line = ''
        newlines.append(line)
    return newlines


def remove_inline_comments(lines):
    return map(lambda x: remove_everything_past('//', x), lines)


def minify_operator(op):
    to_compile = " *{} *".format(re.escape(op))
    regex = re.compile(to_compile)
    repl = op
    if op in SPACED_OPS:
        repl += " "
    return lambda string: regex.sub(repl, string)
def fix_spaced_ops(minified_txt):
    for op in SPACED_OPS:
        pattern = "{} {{".format(op)
        repl = "{}{{".format(op)
        minified_txt = re.sub(pattern, repl, minified_txt)
    return minified_txt
def fix_unary_operators(lines):
    regex_unary_ops = '[{}]'.format(''.join(UNARY_OPS))
    regex_unary_ops = re.escape(regex_unary_ops)
    pattern = r"^(#[a-z]+ +[\w\d]+)([{}][\w\d]+)$".format(regex_unary_ops)
    repl = r'\1' + " " + r'\2'
    for (idx, line) in enumerate(lines):
        if is_preprocessor_directive(line):
            for op in UNARY_OPS:
                line = re.sub(pattern, repl, line)
            lines[idx] = line
    return lines
def clear_whitespace_first_pass(lines):
    lines = map(lambda x: x.replace('\t', ' '), lines)
    # specify only spaces so it doesn't strip newlines
    lines = map(lambda x: x.strip(' '), lines)
    return list(lines)


def reinsert_preprocessor_newlines(lines):
    for idx, line in enumerate(lines):
        if is_preprocessor_directive(line) or (
         idx != len(lines)-1 and is_preprocessor_directive(lines[idx+1])):
            lines[idx] = lines[idx] + '\n'
    return lines
def fix_duplicate_newlines(file):
    regex = re.compile('[\n]{2,}')
    return regex.sub('\n', file)
def is_preprocessor_directive(line):
    return line.startswith(PREPROCESSOR_TOKEN)
def minify_source(orig_source, args=None):
    keep_newlines = getattr(args, 'keep_newlines', False)
    keep_multiline_comments = getattr(args, 'keep_multiline', False)
    keep_inline_comments = getattr(args, 'keep_inline', False)
    lines = orig_source.split('\n')
    lines = clear_whitespace_first_pass(lines)
    if keep_newlines is False:
        lines = reinsert_preprocessor_newlines(lines)
    for op in OPS:
        lines = map(minify_operator(op), lines)
    if keep_inline_comments is False:
        lines = remove_inline_comments(lines)
    if keep_multiline_comments is False:
        lines = remove_multiline_comments(lines)
    multi_spaces = re.compile(r'[  ]+ *')
    lines = list(map(lambda string: multi_spaces.sub(' ', string), lines))
    lines = fix_unary_operators(lines)
    minified = ""
    if keep_newlines is True:
        minified = args.newline.join(lines)
    else:
        minified = fix_duplicate_newlines(''.join(lines))
    minified = fix_spaced_ops(minified)
    return minified
def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("files", nargs='+', help="Input files")
    parser.add_argument("-n", "--names",
                        help="Show name of processed files",
                        action='store_true')
    parser.add_argument("-s", "--stats",
                        help="Show statistics on minified version",
                        action='store_true')
    parser.add_argument("-m", "--keep-multiline",
                        help="Don't strip multiline comments (/* ... */)",
                        action='store_true')
    parser.add_argument("-i", "--keep-inline",
                        help="Do not strip inline comments (// ...)",
                        action='store_true')
    parser.add_argument("-w", "--keep-newlines",
                        help="Keep newline control characters",
                        action='store_true')
    args = parser.parse_args()
    return args
def get_minification_delta(source_text, minified_text):
    orig_size = len(source_text)
    mini_size = len(minified_text)
    delta = orig_size - mini_size
    return delta
def print_additional_info(orig_source, minified_source, filename, args):
    if args.names is True:
        print("{}:".format(filename))
    if args.stats is True:
        orig_size = len(orig_source)
        mini_size = len(minified_source)
        delta = get_minification_delta(orig_source, minified_source)
        if orig_size != 0:
            print(
                "Original: {0} characters, Minified: {1} characters, {2} removed ({3:.1f}%)"
                .format(orig_size, mini_size, delta, (float(delta) / float(orig_size)) * 100.0)
            )
def process_files(args):
    for filename in args.files:
        orig_source_code = ""
        newline = None
        if filename == "-":
            for line in fileinput.input():
                orig_source_code += line
        else:
            with open(filename, 'r') as f:
                orig_source_code = f.read()
                newline = f.newlines
        if type(newline) is tuple:
            print(
                "Mixed newlines are unsupported, skipping file {}."
                .format(filename)
            )
            continue
        args.newline = newline
        minified_source_code = minify_source(orig_source_code, args)
        print_additional_info(
            orig_source_code, minified_source_code, filename, args
        )
        print(minified_source_code)
def main():
    args = get_args()
    process_files(args)
if __name__ == "__main__":
    main()
