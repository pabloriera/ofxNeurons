echo "-------------------------------------->"
echo "CLEANING..."
make clean
echo "-------------------------------------->"
echo "COMMITING..."
git commit -a -m $1
echo "-------------------------------------->"
echo "PUSHING..."
git push
