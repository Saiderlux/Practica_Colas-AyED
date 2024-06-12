Set objShell = CreateObject("WScript.Shell")

For i = 1 To 11
    objShell.SendKeys "^{-}"
    ' WScript.Sleep 500 ' Espera 500 milisegundos entre cada envío 
Next
