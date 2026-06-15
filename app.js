const express = require('express');
const app = express();
const port = 3000;

app.get('/', (req, res) => {
  res.send('<h1>Hello from the Dev Environment! Version 2</h1>');
});

app.listen(port, () => {
  console.log(`Dev app listening on port ${port}`);
});
