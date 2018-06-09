FROM node:8

ENV PORT=3000

RUN mkdir /app

WORKDIR /app

COPY package* ./

RUN npm install --production

COPY . .

EXPOSE 3000

CMD [ "node", "app" ]
