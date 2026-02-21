This software is a simple bit of code that intends to make your live as a STC easier. it comes with simple functionality to let you enter ships into the programm, the program then takes care of how long the ship was docked and calculates the fine for you. Lastly it repetadly reminds you every few min(2.5 min by default) if any ships are overparking and how much they owe you.

The program comes with a help command that explains all commands but here is a summery and some examples:<br>
- help -> displays a help screen.<br>
- assign -> takes 2 arguments and assigns the ship to the given dock example "assign.a1.CIV-451" this assigns dock a1 to the ship CIV-451.
- unassign -> unassigns the ship at the given dock example "unassign.a1" would remove CIV-451 from the tracker.
- unassign_name -> unassigns the ship with a given name example "unassign_name.CIV-451" would remove the ship CIV-451 at dock a1 from the tracker.
- print -> prints all current tracked statistics about all ships.
- cls -> clears the console
- config -> allowes you to ajust the variables used for fining and disable the auto alert system, example "config.auto_alert.true" will enable the auto alert system

Ajustable variables using the config command(potential config file is planed that allow saving the desired values):
- "fine_start_time" this variable needs to be entered in MS and defines after what time the base fine is applied and the additional time based fine. min to ms math: ms / 60000 = min | default = 15min
- "fine_per_second" this variable is a double and is applied every second past the fine_start_time | default = 16.6666 ~ 1k per min
- "base_fine" this variable defines the base fine that is applied once when fine_start_time is surpassed by the docking time of a ship | default= 15000
- "auto_alert_time" this variable needs to be entered in MS and defines the interval for the automated alert if any ships are overparking and how much they owe. | default = 2.5 min
- "auto_alert" this variable can be set to false to disable the auto alert system. | default=true
