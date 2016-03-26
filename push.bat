@echo off
if "%*"=="" (
	set MESSAGE="Message"
) else (
	set MESSAGE="%*"
)

git add . -Av
git commit -m %MESSAGE%
git push origin HEAD
