if [[ $1 ]]; then
	if [[ $1 -eq "+run" ]]; then
		echo "Make script ran with flag: +run"
		echo "Making 'Text Ottitor' executable"
		gcc main.c canvas.c app.c -o 'Text Ottitor'
		echo "Running 'Text Ottitor'"
		./'Text Ottitor' $2
	fi
	else
		echo "Making 'app' executable"
		gcc main.c canvas.c app.c -o app
fi
