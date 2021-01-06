# TriviadorHack
A C++ console applicatoin for the popular online game Triviador

This cheat program is NOT ILLEGAL as it complies with "THX GAMES LTD" Terms of Service.
It is however considered as "content-related damage" which may result in 
"temporary or permanent filtering, point deduction, banning or exclusion from the site" 
by "THX GAMES LTD" End User License Agreement.

I'm not using it nor do I intend to anytime in the future. This was a curious 
experiment to see how easy it was to create a hack for an online quiz game. 
This completely ruined the whole experience for me and I'm never to play any
such game again.

"TriviadorHack" uses Windows API to take real-time screenshots of the game which
are then passed to Tesseract OCR for text extraction. No DB, just read/write to 
binary files. Using Windows API again we simulate key strokes from the keyboard
to insert answers for better reaction times. A simple UI built with 
C++/CLR Windows Forms extension for Visual Studio. Utilized use of multithreading
for better results.
