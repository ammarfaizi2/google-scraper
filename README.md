
# Google Scraper

## Installation for Ubuntu 16.xx / 18.xx

```shell
git clone https://github.com/ammarfaizi2/google-scraper
cd google-scraper
sudo php build.php
cd public && php -d extension=$(pwd)/../google-scraper.so -S 0.0.0.0:3000
```


Usage Example:
http://localhost/api.php?q=es+teh&page=3