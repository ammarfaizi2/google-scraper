
# Google Scraper

## Installation for Ubuntu 16.xx / 18.xx

```shell
sudo apt-add-repository ppa:ondrej/php -y

sudo apt update -y

sudo apt install libphp7.3-embed php7.3 php7.3-bcmath php7.3-bz2 php7.3-cgi php7.3-cli php7.3-common php7.3-curl php7.3-dba php7.3-dev php7.3-enchant php7.3-fpm php7.3-gd php7.3-gmp php7.3-imap php7.3-interbase php7.3-intl php7.3-json php7.3-ldap php7.3-mbstring php7.3-mysql php7.3-odbc php7.3-opcache php7.3-pgsql php7.3-phpdbg php7.3-pspell php7.3-readline php7.3-recode php7.3-snmp php7.3-soap php7.3-sqlite3 php7.3-sybase php7.3-tidy php7.3-xml php7.3-xmlrpc php7.3-xsl php7.3-zip -y

sudo apt install libcurl4-gnutls-dev libpcre3-dev -y

git clone https://github.com/ammarfaizi2/google-scraper

cd google-scraper

sudo php build.php

cd public && php -S 0.0.0.0:3000
```


# Usage Example:

### Google Search
http://localhost:3000/google_search.php?q=berita%20terkini&page=5


### Google Image Search
http://localhost:3000/google_image.php?q=ice%20tea&page=5
