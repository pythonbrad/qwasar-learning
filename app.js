const db = require('./database.js');
const express = require('express');
const app = express();
const port = 8080;


const authenticate = (req, res, next) => {
    const authHeader = req.headers.authorization;

    if (authHeader) {
        const auth = Buffer.from(authHeader.split(' ')[1], 'base64').toString().split(':');
        const username = auth[0];
        const password = auth[1];

        if (username === 'admin' && password === 'admin') {
            next();
        } else {
            res.status(401).send('Authentication failed');
        }
    } else {
        res.status(401).set('WWW-Authenticate', 'Basic realm="Restricted Area"').send('401 Not authorized');
    }
};

app.get('/', (req, res) => {
	var id = (Math.random() * db.frank_sinatra_songs.length).toFixed();

	res.send(db.frank_sinatra_songs[id][0]);
});

app.get('/birth_date', (req, res) => {
	res.send("December 12, 1915");
});

app.get('/birth_city', (req, res) => {
	res.send("Hoboken, New Jersey, U.S");
});

app.get('/wives', (req, res) => {
	res.send("Nancy Barbato, Ava Gardner, Mia Farrow, Barbara Marx");
});

app.get('/picture', (req, res) => {
	res.redirect("https://en.wikipedia.org/wiki/Frank_Sinatra#/media/File:Frank_Sinatra2,_Pal_Joey.jpg");
});

app.get('/public', (req, res) => {
	res.send("Everybody can see this page");
});

app.get('/protected', authenticate, (req, res) => {
	res.send("Welcome, authenticated client");
});

app.listen(port, () => {
	console.log(`Listening on port ${port}...`)
});
