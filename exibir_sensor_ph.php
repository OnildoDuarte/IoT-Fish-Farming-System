<?php
include 'sensorPH.php';

$query = "SELECT ph_valor, datahora FROM ph ORDER BY id DESC LIMIT 1";

// Execute a consulta
$result = $conn->query($query);

if ($result->num_rows > 0) {
    // Exiba os dados
    while ($row = $result->fetch_assoc()) {
        echo "<hr>";
        echo "<br> pH: " . $row['ph_valor']." ";
        echo " Hora de Resgisto: ".$row['datahora'] . "<br>";
        echo "<hr>";
    }
} else {
    echo "Nenhum dado encontrado na tabela.";
}

// Feche a conexão com o banco de dados
$conn->close();
?>