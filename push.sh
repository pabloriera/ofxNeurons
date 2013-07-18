echo "-------------------------------------->"
echo "CLEANING..."
make clean
make cleanDebug
make cleanRelease
echo "-------------------------------------->"
echo "COMMITING..."
git commit -a -m $1
echo "-------------------------------------->"
echo "PUSHING..."
git push
