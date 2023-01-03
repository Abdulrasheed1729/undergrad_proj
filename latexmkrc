push @extra_pdflatex_options, '-synctex=1' ;

sub asy {return system("asy -o asy/ '$_[0]'");}
add_cus_dep("asy","eps",0,"asy");
add_cus_dep("asy","pdf",0,"asy");
add_cus_dep("asy","tex",0,"asy");

$max_repeat = 12;
$pdf_mode = 1;


# $cleanup_includes_generated = 0;
# $cleanup_includes_cusdep_generated = 1;

# @generated_exts = ( 'aux', 'bbl', 'bcf', 'fls', 'idx', 'ind', 'lof',
#                     'lot', 'out', 'pre', 'toc',);

# # don't hash calc for deep system dependencies
# $hash_calc_ignore_pattern{'map'} = '^';
# $hash_calc_ignore_pattern{'fmt'} = '^';