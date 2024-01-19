<!DOCTYPE html>
<html>
  <head>

    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta charset="utf-8">
    <title>PC_Demo_2_IoT</title> 
    <link rel="icon" href="icone.png" type="image/png">
     <meta http-equiv="refresh" content="10">     
     <style>
      html {
          font-family: Arial;
          display: inline-block;
          margin: 0px auto;
          text-align: center;
      }
          .sensor {
            background-color: #F8F8FF;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            padding: 20px;
            margin: 20px;
            border-radius: 8px;
            width: 300px;
            display: inline-block;
            text-align: center;
        }

        .actuador {
            background-color: #F8F8FF;
            box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);
            padding: 20px;
            margin: 20px;
            border-radius: 8px;
            width: 310px;
            display: inline-block;
            text-align: center;
        }
      h1 { font-size: 2.65rem; color:#333;}
      h2 { font-size: 2.35rem; color:#008B8B;}
      h3 { font-size: 2.00rem; color:#330000;}

      body{
            background-color:#F5F5F5;
      }
      
      .buttonON {
        display: inline-block;
        padding: 15px 25px;
        font-size: 24px;
        font-weight: bold;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #4CAF50;
        border: none;
        border-radius: 15px;
        box-shadow: 0 5px #999;
      }
      .buttonON:hover {background-color: #3e8e41}
      .buttonON:active {
        background-color: #3e8e41;
        box-shadow: 0 1px #666;
        transform: translateY(4px);
      }
        
      .buttonOFF {
        display: inline-block;
        padding: 15px 25px;
        font-size: 24px;
        font-weight: bold;
        cursor: pointer;
        text-align: center;
        text-decoration: none;
        outline: none;
        color: #fff;
        background-color: #e74c3c;
        border: none;
        border-radius: 15px;
        box-shadow: 0 5px #999;
      }
      .buttonOFF:hover {background-color: #c0392b}
      .buttonOFF:active {
        background-color: #c0392b;
        box-shadow: 0 1px #666;
        transform: translateY(4px);
      }

          .imagem1{
            width: 100px;
            height: 35px;
            margin-left: 30px;}
          .imagem{
            width: 50px;
            height: 35px;
            margin-left: 30px;

          }
    </style>
  </head>
  <body>

      <div>
            <h1>Sistema de Monitoramento e Controle de Peixe em Cativeiro</h1>
        
      </div>

<hr>
    <h2><img src="imagem_sensor.png" class="imagem1">Sensores: </h2>
<hr>
<div class="sensor">
    <h3>Dados Sensor Temperatura:</h3>
    <?php include('exibir_sensor_temperatura.php'); ?>
</div>
<div class="sensor">
    <h3>Dados Sensor pH:</h3>

    <?php include('exibir_sensor_ph.php'); ?>
</div>
<hr>
    <h2><img src="imagem_actuador.png" class="imagem">Actuadores:</h2>
<hr>
<div class="actuador">
    <h3>Bomba de Água</h3>
    
    <form action="updateDBLED.php" method="post" id="LED_ON_Bomba" onsubmit="myFunction()">
      <input type="hidden" name="Stat" value="1"/>    
    </form>
    
    <form action="updateDBLED.php" method="post" id="LED_OFF_Bomba">
      <input type="hidden" name="Stat" value="0"/>
    </form>
    
    <button class="buttonON" name= "subject" type="submit" form="LED_ON_Bomba" value="SubmitLEDON" >LIGAR</button>
    <button class="buttonOFF" name= "subject" type="submit" form="LED_OFF_Bomba" value="SubmitLEDOFF">DESLIGAR</button>

   <hr>
         Estado: <?php include('exibirLED.php'); ?>
   <hr>
</div>

<div class="actuador">
    <h3>Alimentador</h3>

    <form action="updateDBAlimentador.php" method="post" id="LED_ON_Alimentador" onsubmit="myFunction()">
      <input type="hidden" name="Stat" value="1"/>    
    </form>
    
    <form action="updateDBAlimentador.php" method="post" id="LED_OFF_Alimentador">
      <input type="hidden" name="Stat" value="0"/>
    </form>
    
    <button class="buttonON" name= "subject" type="submit" form="LED_ON_Alimentador" value="SubmitLEDON" >LIGAR</button>
    <button class="buttonOFF" name= "subject" type="submit" form="LED_OFF_Alimentador" value="SubmitLEDOFF">DESLIGAR</button>

    <hr>
          Estado: <?php include('exibirAlimentador.php'); ?>
    <hr>
   </div>

  </body>
</html>
