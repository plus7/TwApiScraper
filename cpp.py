#!/usr/bin/env python
import popen2
cmd = "ls apis/"
(stdout, stdin, stderr) = popen2.popen3( cmd )

for line in stdout:
    line

