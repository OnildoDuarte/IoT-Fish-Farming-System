<?php
// Conectar ao banco de dados
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dbStatusled";

$conn = new mysqli($servername, $username, $password, $dbname);

// Verificar a conexão
if ($conn->connect_error) {
    die("Erro de conexão: " . $conn->connect_error);
}

// Consultar o status do LED
$sql = "SELECT Stat FROM statusled";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // Saída de dados de cada linha
    while ($row = $result->fetch_assoc()) {
        $stat = $row["Stat"];

        // Exibir conteúdo HTML com base no status
        if ($stat == 1) {
            echo "ON";
        } elseif ($stat == 0) {
            echo "OFF";
        } else {
            echo "Status inválido.";
        }
    }
} else {
    echo "Sem resultados na tabela.";
}

// Fechar a conexão
$conn->close();
?>