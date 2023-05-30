PROJECTNAME=main
BUILDDIR=build

.PHONY: $(PROJECTNAME).pdf all clean

all: $(PROJECTNAME).pdf

$(PROJECTNAME).pdf: $(PROJECTNAME).tex
	latexmk -pdf -synctex=1 -verbose -bibtex -interaction=nonstopmode -file-line-error -output-directory=$(BUILDDIR) $<

clean:
	latexmk -output-directory=$(BUILDDIR) -c && rm -rf build/*

## For dev
run:
	latexmk main.tex -bibtex -pvc -f
# clear:
# 	latexmk main.tex -CA
# bib-gen:
# 	cd tex/ && latex main && bibtex main && latex main