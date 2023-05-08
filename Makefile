run:
	latexmk tex/main.tex -pvc -f
clear:
	latexmk tex/main.tex -CA
bib-gen:
	cd tex/ && latex main && bibtex main && latex main