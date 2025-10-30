import os

INCL = 0
PLAIN = 1
MACRO = 2

CONSUME = 0
NO_CONSUME = 1
REPLACE = 2

def next_mode(current, inpt):
    #print(f"[Analizing]: {inpt}")
    #print(f"[Mode]: {current}")
    if current == PLAIN:
        if inpt == "// @inclStart":
            return (INCL, CONSUME)
        if inpt == "typedef int t;":
            return (MACRO, REPLACE)
        return (PLAIN, NO_CONSUME)
    if current == INCL:
        if inpt == "// @inclEnd":
            return (PLAIN, CONSUME)
        return (INCL, NO_CONSUME)
    return (MACRO, NO_CONSUME)

def gen_for_file(name, in_file, incls: list[str], lines: list[str]):
    mode = PLAIN
    wtd = NO_CONSUME
    for line in in_file:
        line_ = line.strip()
        nmode = next_mode(mode, line_)
        mode = nmode[0]
        wtd = nmode[1]
        if (mode == INCL):
            #print("KUKU # INCL")
            if wtd == NO_CONSUME:
                incls.append(line_)
        if (mode == PLAIN):
            #print("KUKU # PLAIN")
            if wtd == NO_CONSUME:
                lines.append(line_)
        if (mode == MACRO):
            #print("KUKU # MACRO")
            if wtd == REPLACE:
                lines.append("#define " + name + "_MKTYPE(t) \\")
            if wtd == NO_CONSUME:
                lines.append(line_.replace("_1_", "##") + " \\")
    lines.append("\n")


out = open("./out/kcj_gda.h", "w")

out.write("#ifndef __KCJ_GDS_H__\n")

incls = []
lines = []
with os.scandir("./raw") as entries:
    for entry in entries:
        if not entry.is_file():
            continue
        fl = open("./raw/" + entry.name, "r")
        name = entry.name.replace(".c", "").upper()
        gen_for_file(name, fl, incls, lines)
        fl.close()

for incl in incls:
    out.write(incl + "\n")

out.write("\n")

for line in lines:
    out.write(line + "\n")

out.write("#define __KCJ_GDS_H__\n")
out.write("#endif\n")
out.close()