PROJECTNAME=main
BUILDDIR=build

.PHONY: $(PROJECTNAME).pdf all clean

all: $(PROJECTNAME).pdf

$(PROJECTNAME).pdf: $(PROJECTNAME).tex
	latexmk -pdf -synctex=1 -verbose -bibtex -pvc -interaction=nonstopmode -file-line-error -output-directory=$(BUILDDIR) $<

clean:
	latexmk -output-directory=$(BUILDDIR) -c && rm -rf build/*

## For dev
beamer:
	latexmk tex/beamer.tex -bibtex -pvc -f
# clear:
# 	latexmk main.tex -CA
# bib-gen:
# 	cd tex/ && latex main && bibtex main && latex main