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

include('assets/config.inc');
include('assets/fonctions.inc.php');

$conn = init();

if (@$_POST['cmd']=='Délai'){
	set_config('delai',$_POST['sec']);
}
$delai = get_config("delai");

if (@$_POST['cmd']=='RAZ'){
	raz();
}
set_config('step', get_config('step') +1);

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

update_prices();

close_page($delai);

?>
