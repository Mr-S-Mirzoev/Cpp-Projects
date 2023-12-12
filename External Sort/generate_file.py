import argparse
import random
import string
import sys

from tqdm import trange


def init_argparse() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="generate_file",
        formatter_class=argparse.MetavarTypeHelpFormatter,
        description="Generate a file of A-Z symbols",
    )
    parser.add_argument(
        "-q",
        "--lines",
        type=int,
        default=100,
        help="quantity of lines in generated file",
    )
    parser.add_argument(
        "-l", "--max_line_length", type=int, default=1000, help="max length"
    )
    parser.add_argument(
        "-o", "--output", type=str, default="input.txt", help="output filename"
    )
    return parser


def generate_string(max_length: int) -> string:
    N = random.randint(10, max_length)
    return "".join(random.choices(string.ascii_uppercase, k=N))


def generate_file(output: str, lines: int, max_line_length: int):
    with open(output, "w") as f:
        t = trange(lines, desc="Writing lines", leave=True)
        for _ in t:
            f.write(generate_string(max_line_length) + "\n")


def main():
    parser = init_argparse()
    args = parser.parse_args()

    print(
        f"Generating {args.output} with {args.lines} lines each no longer than {args.max_line_length}"
    )

    try:
        generate_file(
            args.output,
            args.lines,
            args.max_line_length,
        )
    except Exception as e:
        print(f"Got generation error: {e}", file=sys.stderr)


if __name__ == "__main__":
    main()
