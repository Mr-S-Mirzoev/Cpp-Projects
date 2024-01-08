import argparse
import subprocess


def run_test(test, bin_dir, count):
    for i in range(count):
        try:
            output = subprocess.check_output([f"{bin_dir}/{test}"])
            expected_output = open(f"{test}_out.txt").read()
            if output.decode().strip() != expected_output.strip():
                print(f"Test {i+1} failed: Output doesn't match expected")
        except subprocess.CalledProcessError:
            print(f"Test {i+1} failed: Code crashed")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-t", "--test", help="Name of the test application")
    parser.add_argument(
        "-d",
        "--bin_dir",
        help="Directory containing the test application binary",
    )
    parser.add_argument(
        "-n", "--count", type=int, help="Number of times to run the test"
    )
    args = parser.parse_args()

    run_test(args.test, args.bin_dir, args.count)
