<?php

function init(){

  $servername = "localhost";
  $username = "<user>";
  $password = "<pass>";
  $dbname = "drinks";

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
          $style = 'up';
        } else if ($row['taux'] < -2.0){
          $style = 'down';
        } else {
          $style = 'normal';
        }

          echo "<tr><td>" . $row["name"]. "</td><td>Price:</td><td>" . $row["price"]."</td><td id='$style'>" . $row["taux"]."%</td></tr>";

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
          $taux = round(rand(-100,100)/1000,4);
          $delta = round($row["price"]*$taux,2);
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
            <a href="index.html" class="logo">
              <span class="title">Wall Drink</span>
            </a>

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
            <h1>Tarif des breuvages</h1>
            <p>Avec modération</p>
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
    <li>&copy; xDM Consulting. All rights reserved</li><li>Design: <a href="http://html5up.net">HTML5 UP</a></li>
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
