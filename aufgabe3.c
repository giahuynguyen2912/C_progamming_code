int f(int i) { 
	printf( "called f\n" ); 
		if (i < 0){ 
			return -i; 
		}else{
			return 3 * i; 
		}
}

/*Die Funktion f nimmt i als Parameter an. Wenn i kleiner als 0 ist,
wird positives i zurückgegeben und wenn i großer als oder gleich 0 ist,
gibt Trippel i zurück.*/