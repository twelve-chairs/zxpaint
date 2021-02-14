rm -f *.xpm

for i in *.bmp;
do
  filename="$(cut -d'.' -f1 <<<"$i")"
  convert "$filename".bmp icons"$filename".xpm
  sed -i '' 's/static char/static const char/' icons"$filename".xpm
done