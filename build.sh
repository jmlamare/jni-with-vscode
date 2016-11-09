javac Sample.java 
g++ -g -I$JAVA_HOME/include -I$JAVA_HOME/include/linux -L$JAVA_HOME/{,jre/}lib{,/amd64}{,/server} Sample.cpp -ljvm -o Sample
