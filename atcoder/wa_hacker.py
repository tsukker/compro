# Run this as:
# python wa_hacker.py [N] -- <cmd_line_wa_solution> -- <cmd_line_ac_solution> -- <cmd_line_input_generator>
# Default value of N is 100.

import subprocess
import sys
import threading


# GCJ 2021 interactive_runner.py
class SubprocessThread(threading.Thread):
    def __init__(
        self,
        args,
        stdin_pipe=subprocess.PIPE,
        stdout_pipe=subprocess.PIPE,
        stderr_prefix=None,
    ):
        threading.Thread.__init__(self)
        self.stderr_prefix = stderr_prefix
        self.p = subprocess.Popen(args, stdin=stdin_pipe, stdout=stdout_pipe, stderr=subprocess.PIPE)

    def run(self):
        try:
            self.pipeToStdErr(self.p.stderr)
            self.return_code = self.p.wait()
            self.error_message = None
        except (SystemError, OSError):
            self.return_code = -1
            self.error_message = "The process crashed or produced too much output."

    # Reads bytes from the stream and writes them to sys.stderr prepending lines
    # with self.stderr_prefix.
    # We are not reading by lines to guard against the case when EOL is never
    # found in the stream.
    def pipeToStdErr(self, stream):
        new_line = True
        while True:
            chunk = stream.readline(1024)
            if not chunk:
                return
            chunk = chunk.decode("UTF-8")
            if new_line and self.stderr_prefix:
                chunk = self.stderr_prefix + chunk
                new_line = False
            sys.stderr.write(chunk)
            if chunk.endswith("\n"):
                new_line = True
            sys.stderr.flush()


def get_args():
    n = 100
    if sys.argv[1].isdecimal():
        n = int(sys.argv[1])
    sep = [i for i, elm in enumerate(sys.argv) if elm == "--"]
    assert len(sep) == 3
    cmd_line_wa = sys.argv[sep[0] + 1 : sep[1]]
    cmd_line_ac = sys.argv[sep[1] + 1 : sep[2]]
    cmd_line_gen = sys.argv[sep[2] + 1 :]
    return (n, cmd_line_wa, cmd_line_ac, cmd_line_gen)


def get_stdout_to_list(lines, stdout_pipe):
    for line in stdout_pipe:
        lines.append(line.decode())


def get_generated_input(
    lines,
    generator_stdout,
    t_wa_stdin,
    t_ac_stdin,
):
    for line in generator_stdout.read().decode().split("\n"):
        lines.append(line)
        encoded = (line + "\n").encode()
        t_wa_stdin.write(encoded)
        t_ac_stdin.write(encoded)
    t_wa_stdin.close()
    t_ac_stdin.close()


if __name__ == "__main__":
    try:
        cmd_lines = get_args()
    except Exception as e:
        print(e)
        sys.exit(1)
    n, cmd_line_wa, cmd_line_ac, cmd_line_gen = cmd_lines
    for _ in range(n):
        t_gen = SubprocessThread(
            cmd_line_gen,
            stderr_prefix="  sol_gen: ",
        )
        t_wa = SubprocessThread(
            cmd_line_wa,
            stderr_prefix="  sol_wa: ",
        )
        t_ac = SubprocessThread(
            cmd_line_ac,
            stderr_prefix="  sol_ac: ",
        )
        lines_input = []
        t_input = threading.Thread(
            target=get_generated_input,
            args=(
                lines_input,
                t_gen.p.stdout,
                t_wa.p.stdin,
                t_ac.p.stdin,
            ),
        )
        lines_wa = []
        t_gs_wa = threading.Thread(
            target=get_stdout_to_list,
            args=(lines_wa, t_wa.p.stdout),
        )
        lines_ac = []
        t_gs_ac = threading.Thread(
            target=get_stdout_to_list,
            args=(lines_ac, t_ac.p.stdout),
        )
        processes = [t_gen, t_input, t_wa, t_ac, t_gs_wa, t_gs_ac]
        for proc in processes:
            proc.start()
        for proc in processes:
            proc.join()
        if lines_wa != lines_ac:
            print(lines_input)
            print(lines_wa)
            print(lines_ac)
            sys.exit(0)
