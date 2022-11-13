dim shell
set shell = createobject("wscript.shell")
shell.run"cmd /c g++ client.cpp -l ws2_32 -o client"
shell.run"cmd /c g++ server.cpp -l ws2_32 -o server"