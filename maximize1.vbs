Set objShell = CreateObject("WScript.Shell")
rem objShell.SendKeys "{F11}"
For i = 1 To 9
    objShell.SendKeys "^{-}"
    ' WScript.Sleep 500 ' Espera 500 milisegundos entre cada envío 
Next
