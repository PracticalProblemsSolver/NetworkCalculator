DROP DATABASE IF EXISTS cscalc;
CREATE DATABASE cscalc;
\c cscalc;

CREATE TABLE IF NOT EXISTS users(id serial not null,
                                 login varchar(255) NOT NULL UNIQUE,
                                 password varchar(255) NOT NULL,
                                 balance integer NOT NULL,
                                 PRIMARY KEY (id));

TRUNCATE TABLE users;

INSERT INTO users VALUES
                      (1, 'user', 'password', 2),
                      (2, 'admin', '123', 3);

