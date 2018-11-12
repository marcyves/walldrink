<?php

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

include('assets/fonctions.inc');

$conn = init();

if (@$_POST['cmd']=='Délai'){
	set_config('delai',$_POST['sec']);
}
$delai = get_config("delai");

if (@$_POST['cmd']=='RAZ'){
	raz();
}
set_config('step', get_config('step') +1);

update_prices();

open_page($delai);

$sql = "SELECT DISTINCT category FROM drinks ORDER BY category";
$cat_result = $conn->query($sql);

if ($cat_result->num_rows > 0) {
		// output data of each row
		$i = 0;

		echo "<section class='tiles'>";

		while($row = $cat_result->fetch_assoc()) {
			$i++;
			if ($i > 6){
				$i=0;
			}

			echo '<article class="style'.$i.'">';
			echo "<h2>".$row['category']."</h2>";

			list_category($row['category']);

			 echo '</article>';
		}
		echo "</section>";
	}

close_page($delai);

?>
