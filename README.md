# walldrink

Walldrink is a very simple application initialy developed to display beverage prices like stocks at the stock exchange.

You can choose the delai between 2 updates from the main window.

BTW, there is only ONE window. No administration (you have to enter the beverage list directly into the database) and the only 2 personalizations allowed are:

 * reset step to 0
 * change delai value

 
Even if this is fully functional, many improvements can be done, feel free to comment, fork and have fun!

## installation

There is no installation (I'm too lazy, sorry)! 

This is what you need to perform in order to have your WallDrink up and running:

 * Get some sort of PHP/MySQL web server (Apache, Nginx)
 * Go to `assets` and copy `config-dist.inc` to `config.inc`
 * In `config.inc` customize $servername, $username, $password and $dbname to your liking
 * In MySQL, create the database `drink` or whatever name you gave it
 * Create the Table and Import the data in the database with the script provided in `install/drinks_2019-02-15.sql`
 * Open index.php in your Browser, voilà!

Et surtout n'oubliez pas d'apprécier avec modération

## vous avez aimé ?
Pourquoi pas me remercier en m'offrant un café ?

<a href="https://www.buymeacoffee.com/marcyves" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-blue.png" alt="Buy Me A Coffee" width="210" ></a>

Réalisé par [@marcyves](https://github.com/marcyves)
