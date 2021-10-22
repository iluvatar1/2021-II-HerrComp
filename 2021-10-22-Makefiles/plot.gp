set xlabel 'Nterm'; set ylabel 'Diff %'
set term pdf; set out "fig.pdf"
plot 'datos.txt' w l t 'Diferencia porcentual'
