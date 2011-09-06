Scribd CCK field for Drupal
===========================

This module allows you to have a [Drupal][] [filefield][] connected to
[Scribd][], so when a file is uploaded to the filefield, it is
automatically passed on to Scribd for processing, and when the node is
displayed, the Scribd iPaper can be rendered on the page for easy
browsing of the document.


Instructions for use
--------------------
First, add an API key from your Scribd account at admin/settings/scribdfield.

Get it here, once you've created an account on Scribd and are logged in. http://www.scribd.com/developers/signup_api_details

When you have it, under Your Name -> Settings, there will be an extra tab, API.

You can also choose to secure your PDFs.  If you so choose, they'll be secured through Scribd and be un-downloadable.  You'll need to get an API secret form Scribd in this case and add it.

You can also disable printing on your Scribd files, which requires that you also enable secure PDFs options as well as enter an API secret.  What's the point of disabling printing on a file users can download?

Another thing, if you change your security settings, the files you've previously uploaded won't work.

Currently, multiple items per field don't work.

If you change your settings, they will not apply retroactively to previously uploaded files.

To add a new Scribd field, go to a CCK content type and add a filefield, of type Scribd Upload.

