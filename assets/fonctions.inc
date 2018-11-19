<?php
/*
==============================================================================

	Copyright (c) 2018 Marc Augier

	For a full list of contributors, see "credits.txt".
	The full license can be read in "license.txt".

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	See the GNU General Public License for more details.

	Contact: m.augier@me.com
==============================================================================
*/


function init(){
  global $servername, $username, $password, $dbname;

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
      die("Connection failed: " . $conn->connect_error);
  }

return $conn;
}

function raz(){
  global $conn;

  $sql = "UPDATE config SET value = 0 WHERE name = 'step'";
  $result = $conn->query($sql);

  $sql = "UPDATE drinks SET taux = 0";
  $result_update = $conn->query($sql);

  $sql = "SELECT DISTINCT id, init_price FROM drinks";
  $result = $conn->query($sql);
  if ($result->num_rows > 0) {
      while($row = $result->fetch_assoc()) {
          $sql = "UPDATE drinks SET price = ".$row['init_price']." WHERE id = '".$row['id']."'";
          $result_update = $conn->query($sql);
      }
  }

}


function set_config($name, $value){
  global $conn;

  $sql = "UPDATE config SET value = $value WHERE name = '$name'";
  $result = $conn->query($sql);
}

function get_config($name){
  global $conn;

  $sql = "SELECT DISTINCT value FROM config WHERE name = '$name'";
  $result = $conn->query($sql);
  $row = $result->fetch_assoc();

  return $row['value'];
}

function list_category($category){
  global $conn;

  $sql = "SELECT * FROM drinks WHERE category = '$category' ORDER BY name";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
      // output data of each row
      echo '<table>';
      while($row = $result->fetch_assoc()) {
        if ($row['taux'] > 2.0){
          $style = 'down';
        } else if ($row['taux'] < -2.0){
          $style = 'up';
        } else {
          $style = 'normal';
        }

          echo "<tr><td>" . $row["name"]. "</td><td>" .
               $row["Contenance"] .
               "</td><td class='price'>" .
               number_format($row["price"], 2, ',', ' ') .
               "</td><td id='$style'>" .
               number_format($row["taux"], 2, ',', ' ')."%</td></tr>";
      }
      echo '</table>';
  } else {
      echo "0 results";
  }

}

function update_price($id, $price, $taux){
  global $conn;

  $sql = "UPDATE drinks SET price = $price, taux = $taux WHERE id = $id";
  $result = $conn->query($sql);

}
function update_prices(){
  global $conn;

  $sql = "SELECT * FROM drinks";
  $result = $conn->query($sql);

  if ($result->num_rows > 0) {
      // output data of each row

// debug      echo '<table>';
      while($row = $result->fetch_assoc()) {
          $step = get_config('step');
          if ($step<20){
            $taux  = round(rand(-20,60)/1000,4);

          } else if ($step<40){
            $taux  = round(rand(-40,80)/1000,4);

          } else {
            $taux  = round(rand(-100,100)/1000,4);
          }
          $delta = round($row["price"]*$taux,1);
          $price = $row["price"]+$delta;

          if ($price > $row['max_price']){
            $price = $row['max_price'];
          }

          if ($price < $row['min_price']){
            $price = $row['min_price'];
          }

          $taux = $taux*100.0;

          update_price($row['id'], $price, $taux);

// debug         echo "<tr><td>" . $row["name"]. "</td><td>Old Price:</td><td>" . $row["price"]."</td><td>New Price:</td><td>$price</td><td>Taux:</td><td>$taux %</td><td>Delta:</td><td>$delta</td></tr>";

      }
// debug      echo '</table>';
  } else {
      echo "0 results";
  }


}

/* (Very simple) Templating functions */

function open_page($delai){

  if ($delai<30) {
    $delai = 30;
  }
  $step = get_config("step");

 ?>
<!DOCTYPE HTML>
<!--
	Phantom by HTML5 UP
	html5up.net | @ajlkn
	Free for personal and commercial use under the CCA 3.0 license (html5up.net/license)
-->
<html>
	<head>
		<title>Wall Drink</title>
<?php

echo '<meta http-equiv="refresh" content="'.$delai.'"/>'

?>

<meta charset="utf-8" />
<meta name="viewport" content="width=device-width, initial-scale=1, user-scalable=no" />
<link rel="stylesheet" href="assets/css/main.css" />
<noscript><link rel="stylesheet" href="assets/css/noscript.css" /></noscript>
</head>
<body class="is-preload">
<!-- Wrapper -->
  <div id="wrapper">
    <!-- Header -->
      <header id="header">
        <div class="inner">
          <!-- Logo -->
            <a href="index.html" class="logo"><img height="120" src="images/logo.png"></a>
          <!-- Nav -->
        </div>
        <div id="header" class="logo">
          <?php echo $step; ?>
        </div>
      </header>

    <!-- Main -->
      <div id="main">
        <div class="inner">
          <header>
            <h1>Gala ISG 2018</h1>
            <h2>Tarif des breuvages</h2>
            <p>Avec modération...</p>
          </header>
<?php

}

function close_page($delai){
  global $conn;

  $conn->close();

?>
</div>
</div>

<!-- Footer -->
<footer id="footer">
  <form method="post" action="index.php">
    <ul class="actions">
      <li><input type="submit" name="cmd" value="RAZ" class="small" /></li>
      <li><input type="text" name="sec" value="<?php echo $delai; ?>" size="3"><input type="submit" name="cmd" value="Délai" class="small" /></li>
    </ul>
</form>
<div class="inner">
  <ul class="copyright">
    <li><img height="35" src="images/xdm.png"> &copy; xDM Consulting. All rights reserved</li><li>Design: <a href="http://html5up.net">HTML5 UP</a></li>
  </ul>
</div>
</footer>

</div>

<!-- Scripts -->
<script src="assets/js/jquery.min.js"></script>
<script src="assets/js/browser.min.js"></script>
<script src="assets/js/breakpoints.min.js"></script>
<script src="assets/js/util.js"></script>
<script src="assets/js/main.js"></script>

</body>
</html>
<?php
}


?>
