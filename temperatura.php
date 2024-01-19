<?php
#Meu primeiro php
	$hostname = "localhost";
	$username = "root";
	$password = "";
	$database = "sensores";


	#verificacao da conexao com a base de dados criada
	$conn = mysqli_connect($hostname, $username, $password, $database);

	if (!$conn) {
		die("Falhou conectar: ".mysqli_connect_error());
	}

	//echo "<br> Base de dados conectada!";



	if(isset($_POST["temperatura"])){

	$t = $_POST["temperatura"];
	//$t = 30;
	$sql = "INSERT INTO ds18b20 (temperatura) VALUES (".$t.")";

	if(mysqli_query($conn, $sql)){

			echo "<br>Novos dados salvos, com sucesso!";

	}

	else{
		echo "Erro:".$sql."<br>".mysqli_connect_error($conn);
	}
}


?>