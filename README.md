
# Google Scraper

## Installation for Ubuntu 16.xx / 18.xx

```shell
sudo apt-add-repository ppa:ondrej/php -y

sudo apt update -y

sudo apt install libphp7.2-embed php7.2 php7.2-bcmath php7.2-bz2 php7.2-cgi php7.2-cli php7.2-common php7.2-curl php7.2-dba php7.2-dev php7.2-enchant php7.2-fpm php7.2-gd php7.2-gmp php7.2-imap php7.2-interbase php7.2-intl php7.2-json php7.2-ldap php7.2-mbstring php7.2-mysql php7.2-odbc php7.2-opcache php7.2-pgsql php7.2-phpdbg php7.2-pspell php7.2-readline php7.2-recode php7.2-snmp php7.2-soap php7.2-sqlite3 php7.2-sybase php7.2-tidy php7.2-xml php7.2-xmlrpc php7.2-xsl php7.2-zip -y

sudo apt install libcurl4-gnutls-dev -y

git clone https://github.com/ammarfaizi2/google-scraper

cd google-scraper

sudo php build.php

cd public && php -d extension=$(pwd)/../google-scraper.so -S 0.0.0.0:3000
```


# Usage Example:

### Google Search
https://google.teainside.org/google_search.php?q=berita%20terkini&page=5


### Google Image Search
https://google.teainside.org/google_image.php?q=ice%20tea&page=5
