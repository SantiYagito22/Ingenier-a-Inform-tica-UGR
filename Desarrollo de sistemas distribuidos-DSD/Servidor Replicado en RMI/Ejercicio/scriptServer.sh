#! /bin/sh -e

echo
echo "Compilando con javac ..."
javac *.java

sleep 2

echo
echo "Lanzando replica 2"
gnome-terminal -e "java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy servidorDonacion 1"

echo
echo "Lanzando replica 2"
gnome-terminal -e "java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy servidorDonacion 2"

echo
echo "Lanzando replica 3"
gnome-terminal -e "java -cp . -Djava.rmi.server.codebase=file:./ -Djava.rmi.server.hostname=localhost -Djava.security.policy=server.policy servidorDonacion 3"



