# Endpoints

api route: `/api/v1/`

# Shared

## System status

Get current system status

| Endpoint        | request Type |
| --------------- | ------------ |
| `/systemStatus` | `GET`        |

### Response:

| name     | value  | description                    |
| -------- | ------ | ------------------------------ |
| `status` | String | Should be always "okay"        |
| `ip`     | String | Device local ip                |
| `memory` | int    | free heap memory on the device |

# Client

## Set color

Set LED strip color

| Endpoint    | request Type |
| ----------- | ------------ |
| `/setColor` | `POST`       |

### Response:

| name    | value        | description         |
| ------- | ------------ | ------------------- |
| `red`   | unsinged int | Red value for LED   |
| `green` | unsinged int | Green value for LED |
| `blue`  | unsinged int | Blue value for LED  |

