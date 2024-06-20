Set objShell = CreateObject("WScript.Shell")
For i = 1 To 11
    objShell.SendKeys "^{+}"
   Next