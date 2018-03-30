This file is distributed under the terms of the GNU Lesser General Public License (Lesser GPL)

homework1 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with homework1. If not, see <http://www.gnu.org/licenses/>.

=Description=

The files in homework1 contain the ROS based implementation for
realize three node where first one publish every second a message(contains name,age and bachelor's),
the second one allows the user to select from the keyboard which part of the message to display on the screen
and the last one print the part of the message selected by the user previously.

=Implementation=

The first node(talker) publish every second a message in "chatter" topic .
The second node(listener_keyboard) listen the keyboard and when the user type a key publish a message in
"keyboard/key" topic.
The third node(listener) listen the "chatter" topic and the "keyboard/key" topic and use these information to choose
what part of message to display on the screen.

This is the rqt_graph of the package
![rqt_graph](images/rqt_graph_homework1.png)

Please, report suggestions/comments/bugs to<br>
alessandro.riboni@studenti.univr.it
