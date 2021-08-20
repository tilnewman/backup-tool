# backup-tool
A backup utility for bit perfect copies.

##

Have a lot of files to backup between different drives?  Cloud not an option?  Tired of rsync?  Windows directory merge bugs got you down?  Me too.  So I made Backup-Tool.  It lets you quickly compare two file trees, then backup whatever is different or missing, and if you want, even lets you prune the extras when you’re done.

Backup-Tool compares every bit of every file, not dates or timestamps.  (avoid that nightmare, trust me…)  It also has a mode to run faster and skip checking every bit, but only if you want.  Normally it uses multiple threads and runs blazingly fast, but it also has a mode to stay single-threaded if you want to keep working and run it in the background.  Oh yeah, and it won’t create directories full of support files and hashes.  It burns clean.

Backup-Tool is not intended for cloning operating system files or windows junction files.  You should be using an off-the-shelf drive cloner for that job.  It’s also NOT intended to keep two drives in real-time constant sync.  I suppose you could run it every minute, but come on, you should be using a drive mirroring hardware solution for that.  This is a tool for backing up large collections of files and folders only every so often.  Like a photo or movie collection, or maybe all the junk on you keep putting on that thumb drive.

##
Example Workflow:

* ./backup.exe --compare C:/photos D:/photos
* ./backup.exe --copy C:/photos D:/photos
* ./backup.exe --cull C:/photos D:/photos
