
# Google Scraper

## Installation for Ubuntu 16.xx / 18.xx

```shell
sudo php build.php
cd public && php -d extension=$(pwd)/../google-scraper.so -S 0.0.0.0:3000
```