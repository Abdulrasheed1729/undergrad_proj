run:
	latexmk main.tex -bibtex -pvc -f
clear:
	latexmk main.tex -CA
bib-gen:
	cd tex/ && latex main && bibtex main && latex main