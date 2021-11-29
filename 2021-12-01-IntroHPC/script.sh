echo "First arg: ${1}"
timeout -k 9 10s stress -t 10 -c 1 # stress one core
echo "Stress test done"
