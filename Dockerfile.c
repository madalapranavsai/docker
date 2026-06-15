FROM node:20-alpine AS base
WORKDIR /app
RUN addgroup -S appgroup && adduser -S appuser -G appgroup

FROM base AS deps
COPY package*.json ./
RUN npm install --omit=dev

FROM base AS builder
COPY package*.json ./
RUN npm install
COPY . .

FROM base AS production
COPY --from=deps /app/node_modules ./node_modules
COPY --from=builder /app/app.js ./app.js
USER appuser
HEALTHCHECK --interval=30s --timeout=3s CMD wget -qO- http://localhost:3000/ || exit 1
CMD ["node", "app.js"]