???+note check listening processes
    Check what processes are listening via `netstat -lntp` or `ss -plat` (for TCP; add `-u` for UDP) or `lsof -iTCP -sTCP:LISTEN -P -n` (which also works on macOS).