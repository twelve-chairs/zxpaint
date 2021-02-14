#rm -f *.xpm
#
#for i in *.bmp;
#do
#  # Get file name without extension
#  filename="$(cut -d'.' -f1 <<<"$i")"
#  # Convert BMP to XPM (ImageMagick)
#  convert "$filename".bmp icons"$filename".xpm
#  # Make it compatible with C++11
#  sed -i '' 's/static char/static const char/' icons"$filename".xpm
#done

#
#include='BEGIN: Include all images \
##include "../res/icons"$filename".xpm" \
#
#const auto icons = {
#        &icons"$filename"
#};
#
#//END: Include all images
#'
cd ..
cd src
sed -i '' 's/BEGIN\:(.*)END\: Include all images/farts/' main.h
cd ..
cd res