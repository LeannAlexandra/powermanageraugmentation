# Power Manager Augmentation

<i>Do you have problems with your computer's battery running down in your backpack?</i>

<h2>What Causes this problem</h2>
<p>I am lead to believe that most power managers allow certain funciton (like downloading updates) to continue even in clamshell mode when it is connected to power</p>
<p>This is not a bad thing, but the bad thing about it, is that when the laptop is closed before unplugging, this can run off your battery.</p>
<p>This problem is simply avoided when unpluggin the laptop before closing the lid, but as a perfectionist, I want to throw my two cents in the lot and say this should be an easy kernel fix.</p>
<p>QUESTION: Why isn't it standard feature in OS's? is no one actively complaining, or is no one correctly diagnosing the cause of the phenomena? </p>
<img src="https://media.tenor.com/4L63mLtTaj0AAAAM/why-isnt-it-posssible-its-just-not.gif" alt="Why isn't it possible">

<h2>What does this app do?</h2>
<p>This app registeres a service that checks if the lid is closed once every 10 seconds this is a minimally invasive procedure that wont bog down the system. </p>
<p>If it finds that the lid is closed, it checks if there is ac power.</p>
<p>If there is ac power, it just hangs back. but if there is no ac power, it finds how long the system has been idle </p>
<p>if the system has been closed, unpowered and idle for 5 minutes, the system forcefully goes to sleep </p>

<h2>Supported Systems:</h2>
<ul><li>Linux Manjaro - confirmed on x86_64 Kernel 6.6.10-1
<img src="https://imgflip.com/i/8d5dx2" alt="Why isn't it possible">
</li></ul>

<h2>Want to help out?</h2>
<p>I need to compile the same C language files on different systems to see what needs to change and what happens on compile time, seeing that I don't routinely use those systems my knowledge of them can benefit from your contribution.</p>
<img src="https://plaky.com/blog/wp-content/uploads/2023/08/Works-on-my-machine.jpg" alt="Will you fix it?">
