Complete documentation is available at http://drupal.org/node/598542

*Getting started*
After you install the module, get an API key for your website at http://www.scribd.com/platform/start. 
Enter the API key on the configuration page (/admin/settings/ipaper). 
You can also enter the Secret key to sign all your requests with it. In this case, set "Require signature" in your Scribd API accound. 
After you begin publishing documents you will be able to see the files you uploaded through the Drupal site under "My documents" on scribd.com (www.scribd.com/mydocs).

*Creating iPapers*
After you enter your API key, you should be able to go ahead and create iPaper nodes. Attach a document of the types supported by Scribd and save the node (you cannot save it unless you attach at least one file). 

*Input filter*
Go to Administer input formats (/admin/settings/filters) and enable the iPaper embed filter on any of your existing input formats.

*Permissions*
Remember to set the necessary permissions extended by the module. You should be aware that the module will show more than you need if you are logged on with the administrator account (user 1), because you have all the permissions.
In addition to the self-explanatory "create ipapers", "edit ipapers", "edit own ipapers", "delete ipapers", "delete own ipapers", take note of the following:
-"embed ipapers" shows users a text box with embed code for the current document in node view. This code works even if your document is private.
-"download ipapers" allows users to download a PDF version of the upload (a link is added under the iPaper). The format in which the download is offered can be set in the administration form. The link added to the node is to a Scribd dynamic URL.
-"edit ipaper parameters" is normally useful only to administrators. You might, however, have a setup in which you want to embed documents that are already uploaded, so then you can extend the "edit ipaper parameters" to the users who would enter these parameters manually.

*Help*
Developers, You can find documentation for the API at http://www.scribd.com/platform/documentation/api.
As you work to extend this module, you can find answers at http://www.scribd.com/platform/faq 
and ask questions at http://groups.google.com/group/scribd-platform-developers/topics

Post support requests and bugs at http://drupal.org/project/issues/ipaper
Please include messages and the information the module saved in your site's event log. If you know your question is not related to this module, but instead has to do with how Scribd handles your files, please post in the Scribd forum, not in the iPaper issue queue.

Project created by Rares Pamfil - ipaper.rarespamfil.com