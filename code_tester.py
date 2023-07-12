import subprocess
import os
l=[]
for i in range(1,112):
    print(i)
    s="open_"+str(i)+".txt"
    input=open(s,"r")
    output=open("output.txt","w")
    proc=subprocess.run("./main",stdin=input,stdout=output)
    output.close()
    s="open_"+str(i)+".output.txt"
    proc=subprocess.run(["diff",s,"output.txt"],capture_output=True)
    if proc.stdout.decode() != "":
        l.append(i)
    os.system("clear")

print(l)