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



if(isset($_POST["pH"])){

	$p = $_POST["pH"];
	//$p = 7;
	$sql = "INSERT INTO ph (ph_valor) VALUES (".$p.")";

	if(mysqli_query($conn, $sql)){

			//echo "<br>Novos dados salvos, com sucesso!";

	}

	else{
		echo "Erro:".$sql."<br>".mysqli_connect_error($conn);
	}
}


?>