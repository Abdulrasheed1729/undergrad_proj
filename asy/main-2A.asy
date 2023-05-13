if(!settings.multipleView) settings.batchView=false;
settings.tex="pdflatex";
defaultfilename="main-2A";
if(settings.render < 0) settings.render=4;
settings.outformat="";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2,2);

// import extras;
size(6cm);
usepackage("amsmath");
usepackage("amssymb");
defaultpen(fontsize(11pt));
settings.tex="latex";
settings.outformat="pdf";

draw((0,0) .. (0.025,0.025) .. (0.5,0), Arrow);
draw((0.5,-0.0125) .. (0.025,-0.0375) .. (0,-0.0125), Arrow);
label("$X$", (0,0),W);
label("$Y$", (0.5,0), E);
label("$f$", (0.025,-0.0375));
label("$g$", (0.025,0.025));
