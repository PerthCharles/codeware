#./configure --prefix=/home/zhongbin/programs/rdesktop-test --with-debug --with-debug-kbd --with-debug-rdp5  
#./configure --prefix=/home/zhongbin/programs/rdesktop-test --with-debug --with-debug-rdp5  
#./configure --prefix=/home/zhongbin/programs/rdesktop-test --with-debug  
#./configure --prefix=/home/zhongbin/programs/rdesktop-test --with-debug-rdp5  
./configure --prefix=/home/zhongbin/programs/rdesktop-test
# --with-debug-kbd --with-debug-rdp5  
#./configure --prefix=/home/zhongbin/programs/rdesktop-test --with-debug-kbd
#--with-debug --with-debug-kbd --with-debug-rdp5  
echo "configure complete"
sleep 2
echo "begin to make"
make clean
make
echo "make complete"
sleep 2
echo "begin to install"
make install
echo "install complete!"

